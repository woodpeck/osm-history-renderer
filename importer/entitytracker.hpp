/**
 * The handler always needs to know what the previous node/way/relation
 * in the file looked like to answer questions like "what is the
 * valid_from date of the current entity" or "is this the last version
 * of that entity". The EntityTracker takes care of keeping the
 * current and the previous entity, free them as required and do basic
 * comparations.
 */

#ifndef IMPORTER_ENTITYTRACKER_HPP
#define IMPORTER_ENTITYTRACKER_HPP

/**
 * Tracks a previous and a current entity, provides a method to make the
 * current entity the previous one and manages freeing of the entities.
 * It is templated to allow nodes, ways and relations as child objects.
 */
template <class TObject>
class EntityTracker {

private:
    /**
     * pointer to the previous entity
     */
    shared_ptr<TObject const> m_prev;

    /**
     * pointer to the current entity
     */
    shared_ptr<TObject const> m_cur;

public:
    /**
     * get the pointer to the previous entity
     */
    const shared_ptr<TObject const> prev() {
        return m_prev;
    }

    /**
     * get the pointer to the current entity
     */
    const shared_ptr<TObject const> cur() {
        return m_cur;
    }

    /**
     * returns if the tracker currently tracks a previous entity
     */
    bool has_prev() {
        return m_prev;
    }

    /**
     * returns if the tracker currently tracks a current entity
     */
    bool has_cur() {
        return m_cur;
    }

    /**
     * returns if the tracker currently tracks a previous and a current
     * entity with the same id
     */
    bool cur_is_same_entity() {
        return has_prev() && has_cur() && (prev()->id() == cur()->id());
    }

    /**
     * feed in a new object as the current one
     *
     * if a current one still exists, the program will abort with an
     * assertation error, because the current enity needs to be swapped
     * away using the swap-method below, before feeding in a new one.
     */
    void feed(const shared_ptr<TObject const> obj) {
        assert(!m_cur);
        m_cur = obj;
    }

    /**
     * make the current entity the previous and delete the previous entity
     */
    void swap() {
        m_prev = m_cur;
        m_cur.reset();
    }
};

#endif // IMPORTER_ENTITYTRACKER_HPP
